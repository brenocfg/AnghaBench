#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_log {int dummy; } ;
struct mp_colorspace {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  IDXGISwapChain ;
typedef  scalar_t__ DXGI_FORMAT ;
typedef  int DXGI_COLOR_SPACE_TYPE ;

/* Variables and functions */
 int DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709 ; 
 scalar_t__ DXGI_FORMAT_R8G8B8A8_UNORM ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  IsWindows10OrGreater () ; 
 char* d3d11_get_csp_name (int) ; 
 char* d3d11_get_format_name (scalar_t__) ; 
 int d3d11_get_mp_csp (int,struct mp_colorspace*) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,char const*,int) ; 
 int /*<<< orphan*/  mp_warn (struct mp_log*,char*,char const*,int) ; 
 int /*<<< orphan*/  query_output_format_and_colorspace (struct mp_log*,int /*<<< orphan*/ *,scalar_t__*,int*) ; 
 int /*<<< orphan*/  update_swapchain_color_space (struct mp_log*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_swapchain_format (struct mp_log*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool configure_created_swapchain(struct mp_log *log,
                                        IDXGISwapChain *swapchain,
                                        DXGI_FORMAT requested_format,
                                        DXGI_COLOR_SPACE_TYPE requested_csp,
                                        struct mp_colorspace *configured_csp)
{
    DXGI_FORMAT probed_format = DXGI_FORMAT_UNKNOWN;
    DXGI_FORMAT selected_format = DXGI_FORMAT_UNKNOWN;
    DXGI_COLOR_SPACE_TYPE probed_colorspace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
    DXGI_COLOR_SPACE_TYPE selected_colorspace;
    const char *format_name = NULL;
    const char *csp_name = NULL;
    struct mp_colorspace mp_csp = { 0 };
    bool mp_csp_mapped = false;

    query_output_format_and_colorspace(log, swapchain,
                                       &probed_format,
                                       &probed_colorspace);


    selected_format = requested_format != DXGI_FORMAT_UNKNOWN ?
                      requested_format :
                      (probed_format != DXGI_FORMAT_UNKNOWN ?
                       probed_format : DXGI_FORMAT_R8G8B8A8_UNORM);
    selected_colorspace = requested_csp != -1 ?
                          requested_csp : probed_colorspace;
    format_name   = d3d11_get_format_name(selected_format);
    csp_name      = d3d11_get_csp_name(selected_colorspace);
    mp_csp_mapped = d3d11_get_mp_csp(selected_colorspace, &mp_csp);

    mp_verbose(log, "Selected swapchain format %s (%d), attempting "
                    "to utilize it.\n",
               format_name, selected_format);

    if (!update_swapchain_format(log, swapchain, selected_format)) {
        return false;
    }

    if (!IsWindows10OrGreater()) {
        // On older than Windows 10, query_output_format_and_colorspace
        // will not change probed_colorspace, and even if a user sets
        // a colorspace it will not get applied. Thus warn user in case a
        // value was specifically set and finish.
        if (requested_csp != -1) {
            mp_warn(log, "User selected a D3D11 color space %s (%d), "
                         "but configuration of color spaces is only supported"
                         "from Windows 10! The default configuration has been "
                         "left as-is.\n",
                    csp_name, selected_colorspace);
        }

        return true;
    }

    if (!mp_csp_mapped) {
        mp_warn(log, "Color space %s (%d) does not have an mpv color space "
                     "mapping! Overriding to standard sRGB!\n",
                csp_name, selected_colorspace);
        selected_colorspace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
        d3d11_get_mp_csp(selected_colorspace, &mp_csp);
    }

    mp_verbose(log, "Selected swapchain color space %s (%d), attempting to "
                    "utilize it.\n",
               csp_name, selected_colorspace);

    if (!update_swapchain_color_space(log, swapchain, selected_colorspace)) {
        return false;
    }

    if (configured_csp) {
        *configured_csp = mp_csp;
    }

    return true;
}