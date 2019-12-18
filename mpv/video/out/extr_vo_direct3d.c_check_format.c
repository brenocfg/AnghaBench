#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct fmt_entry {scalar_t__ mplayer_fmt; int /*<<< orphan*/  fourcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  desktop_fmt; int /*<<< orphan*/  d3d_handle; } ;
typedef  TYPE_1__ d3d_priv ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DADAPTER_DEFAULT ; 
 int /*<<< orphan*/  D3DRTYPE_TEXTURE ; 
 int D3DUSAGE_DYNAMIC ; 
 int D3DUSAGE_QUERY_FILTER ; 
 int /*<<< orphan*/  DEVTYPE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3D9_CheckDeviceFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3D9_CheckDeviceFormatConversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMGFMT_IS_ANY_RND (scalar_t__) ; 
 int /*<<< orphan*/  MP_DBG (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ) ; 
 struct fmt_entry* fmt_table ; 
 int /*<<< orphan*/  vo_format_name (scalar_t__) ; 

__attribute__((used)) static D3DFORMAT check_format(d3d_priv *priv, uint32_t movie_fmt,
                              bool as_texture)
{
    const char *type = as_texture ? "texture rendering" : "StretchRect";
    const struct fmt_entry *cur = &fmt_table[0];

    // Don't try to handle weird packed texture formats (although I don't know
    // if D3D9 would even accept any such format for 3D rendering; and we
    // certainly don't try any tricks like matching it to RGB formats and
    // applying a YUV conversion matrix)
    if (as_texture && !IMGFMT_IS_ANY_RND(movie_fmt))
        return 0;

    while (cur->mplayer_fmt) {
        if (cur->mplayer_fmt == movie_fmt) {
            HRESULT res;
            if (as_texture) {
                res = IDirect3D9_CheckDeviceFormat(priv->d3d_handle,
                            D3DADAPTER_DEFAULT,
                            DEVTYPE,
                            priv->desktop_fmt,
                            D3DUSAGE_DYNAMIC | D3DUSAGE_QUERY_FILTER,
                            D3DRTYPE_TEXTURE,
                            cur->fourcc);
            } else {
                /* Test conversion from Movie colorspace to
                * display's target colorspace. */
                res = IDirect3D9_CheckDeviceFormatConversion(priv->d3d_handle,
                            D3DADAPTER_DEFAULT,
                            DEVTYPE,
                            cur->fourcc,
                            priv->desktop_fmt);
            }
            if (FAILED(res)) {
                MP_VERBOSE(priv, "Rejected image format "
                       "(%s): %s\n", type, vo_format_name(cur->mplayer_fmt));
                return 0;
            }

            MP_DBG(priv, "Accepted image format (%s): %s\n",
                   type, vo_format_name(cur->mplayer_fmt));

            return cur->fourcc;
        }
        cur++;
    }

    return 0;
}