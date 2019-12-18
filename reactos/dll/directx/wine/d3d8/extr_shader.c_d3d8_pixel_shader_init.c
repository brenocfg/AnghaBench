#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ element_count; } ;
struct TYPE_5__ {scalar_t__ element_count; } ;
struct TYPE_4__ {scalar_t__ element_count; } ;
struct wined3d_shader_desc {size_t byte_code_size; int max_version; TYPE_3__ patch_constant_signature; TYPE_2__ output_signature; TYPE_1__ input_signature; int /*<<< orphan*/  format; int /*<<< orphan*/  const* byte_code; } ;
struct d3d8_pixel_shader {int /*<<< orphan*/  wined3d_shader; int /*<<< orphan*/  handle; } ;
struct d3d8_device {int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_SHADER_BYTE_CODE_FORMAT_SM1 ; 
 int /*<<< orphan*/  d3d8_pixelshader_wined3d_parent_ops ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int /*<<< orphan*/  wined3d_shader_create_ps (int /*<<< orphan*/ ,struct wined3d_shader_desc*,struct d3d8_pixel_shader*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT d3d8_pixel_shader_init(struct d3d8_pixel_shader *shader, struct d3d8_device *device,
        const DWORD *byte_code, DWORD shader_handle)
{
    struct wined3d_shader_desc desc;
    HRESULT hr;

    shader->handle = shader_handle;

    desc.byte_code = byte_code;
    desc.byte_code_size = ~(size_t)0;
    desc.format = WINED3D_SHADER_BYTE_CODE_FORMAT_SM1;
    desc.input_signature.element_count = 0;
    desc.output_signature.element_count = 0;
    desc.patch_constant_signature.element_count = 0;
    desc.max_version = 1;

    wined3d_mutex_lock();
    hr = wined3d_shader_create_ps(device->wined3d_device, &desc, shader,
            &d3d8_pixelshader_wined3d_parent_ops, &shader->wined3d_shader);
    wined3d_mutex_unlock();
    if (FAILED(hr))
    {
        WARN("Failed to create wined3d pixel shader, hr %#x.\n", hr);
        return hr;
    }

    return D3D_OK;
}