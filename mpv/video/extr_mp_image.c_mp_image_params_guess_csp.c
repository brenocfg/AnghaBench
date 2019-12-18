#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ space; scalar_t__ levels; scalar_t__ gamma; scalar_t__ primaries; int sig_peak; scalar_t__ light; } ;
struct mp_image_params {scalar_t__ chroma_location; TYPE_1__ color; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  enum mp_csp { ____Placeholder_mp_csp } mp_csp ;

/* Variables and functions */
 scalar_t__ MP_CHROMA_AUTO ; 
 scalar_t__ MP_CHROMA_CENTER ; 
 scalar_t__ MP_CHROMA_LEFT ; 
 int MP_CSP_AUTO ; 
 scalar_t__ MP_CSP_BT_2020_C ; 
 scalar_t__ MP_CSP_BT_2020_NC ; 
 scalar_t__ MP_CSP_BT_601 ; 
 scalar_t__ MP_CSP_BT_709 ; 
 scalar_t__ MP_CSP_LEVELS_AUTO ; 
 scalar_t__ MP_CSP_LEVELS_PC ; 
 scalar_t__ MP_CSP_LEVELS_TV ; 
 scalar_t__ MP_CSP_LIGHT_AUTO ; 
 scalar_t__ MP_CSP_LIGHT_DISPLAY ; 
 scalar_t__ MP_CSP_LIGHT_SCENE_HLG ; 
 scalar_t__ MP_CSP_PRIM_AUTO ; 
 void* MP_CSP_PRIM_BT_2020 ; 
 void* MP_CSP_PRIM_BT_709 ; 
 int MP_CSP_RGB ; 
 scalar_t__ MP_CSP_SMPTE_240M ; 
 scalar_t__ MP_CSP_TRC_AUTO ; 
 scalar_t__ MP_CSP_TRC_BT_1886 ; 
 scalar_t__ MP_CSP_TRC_HLG ; 
 scalar_t__ MP_CSP_TRC_LINEAR ; 
 scalar_t__ MP_CSP_TRC_SRGB ; 
 scalar_t__ MP_CSP_TRC_V_LOG ; 
 int MP_CSP_XYZ ; 
 scalar_t__ MP_CSP_YCGCO ; 
 int MP_REF_WHITE ; 
 int mp_csp_guess_colorspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_csp_guess_primaries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_image_params_get_forced_csp (struct mp_image_params*) ; 
 int /*<<< orphan*/  mp_trc_is_hdr (scalar_t__) ; 
 int mp_trc_nom_peak (scalar_t__) ; 

void mp_image_params_guess_csp(struct mp_image_params *params)
{
    enum mp_csp forced_csp = mp_image_params_get_forced_csp(params);
    if (forced_csp == MP_CSP_AUTO) { // YUV/other
        if (params->color.space != MP_CSP_BT_601 &&
            params->color.space != MP_CSP_BT_709 &&
            params->color.space != MP_CSP_BT_2020_NC &&
            params->color.space != MP_CSP_BT_2020_C &&
            params->color.space != MP_CSP_SMPTE_240M &&
            params->color.space != MP_CSP_YCGCO)
        {
            // Makes no sense, so guess instead
            // YCGCO should be separate, but libavcodec disagrees
            params->color.space = MP_CSP_AUTO;
        }
        if (params->color.space == MP_CSP_AUTO)
            params->color.space = mp_csp_guess_colorspace(params->w, params->h);
        if (params->color.levels == MP_CSP_LEVELS_AUTO) {
            if (params->color.gamma == MP_CSP_TRC_V_LOG) {
                params->color.levels = MP_CSP_LEVELS_PC;
            } else {
                params->color.levels = MP_CSP_LEVELS_TV;
            }
        }
        if (params->color.primaries == MP_CSP_PRIM_AUTO) {
            // Guess based on the colormatrix as a first priority
            if (params->color.space == MP_CSP_BT_2020_NC ||
                params->color.space == MP_CSP_BT_2020_C) {
                params->color.primaries = MP_CSP_PRIM_BT_2020;
            } else if (params->color.space == MP_CSP_BT_709) {
                params->color.primaries = MP_CSP_PRIM_BT_709;
            } else {
                // Ambiguous colormatrix for BT.601, guess based on res
                params->color.primaries = mp_csp_guess_primaries(params->w, params->h);
            }
        }
        if (params->color.gamma == MP_CSP_TRC_AUTO)
            params->color.gamma = MP_CSP_TRC_BT_1886;
    } else if (forced_csp == MP_CSP_RGB) {
        params->color.space = MP_CSP_RGB;
        params->color.levels = MP_CSP_LEVELS_PC;

        // The majority of RGB content is either sRGB or (rarely) some other
        // color space which we don't even handle, like AdobeRGB or
        // ProPhotoRGB. The only reasonable thing we can do is assume it's
        // sRGB and hope for the best, which should usually just work out fine.
        // Note: sRGB primaries = BT.709 primaries
        if (params->color.primaries == MP_CSP_PRIM_AUTO)
            params->color.primaries = MP_CSP_PRIM_BT_709;
        if (params->color.gamma == MP_CSP_TRC_AUTO)
            params->color.gamma = MP_CSP_TRC_SRGB;
    } else if (forced_csp == MP_CSP_XYZ) {
        params->color.space = MP_CSP_XYZ;
        params->color.levels = MP_CSP_LEVELS_PC;

        // In theory, XYZ data does not really need a concept of 'primaries' to
        // function, but this field can still be relevant for guiding gamut
        // mapping optimizations, and it's also used by `mp_get_csp_matrix`
        // when deciding what RGB space to map XYZ to for VOs that don't want
        // to directly ingest XYZ into their color pipeline. BT.709 would be a
        // sane default here, but it runs the risk of clipping any wide gamut
        // content, so we pick BT.2020 instead to be on the safer side.
        if (params->color.primaries == MP_CSP_PRIM_AUTO)
            params->color.primaries = MP_CSP_PRIM_BT_2020;
        if (params->color.gamma == MP_CSP_TRC_AUTO)
            params->color.gamma = MP_CSP_TRC_LINEAR;
    } else {
        // We have no clue.
        params->color.space = MP_CSP_AUTO;
        params->color.levels = MP_CSP_LEVELS_AUTO;
        params->color.primaries = MP_CSP_PRIM_AUTO;
        params->color.gamma = MP_CSP_TRC_AUTO;
    }

    if (!params->color.sig_peak) {
        if (params->color.gamma == MP_CSP_TRC_HLG) {
            params->color.sig_peak = 1000 / MP_REF_WHITE; // reference display
        } else {
            // If the signal peak is unknown, we're forced to pick the TRC's
            // nominal range as the signal peak to prevent clipping
            params->color.sig_peak = mp_trc_nom_peak(params->color.gamma);
        }
    }

    if (!mp_trc_is_hdr(params->color.gamma)) {
        // Some clips have leftover HDR metadata after conversion to SDR, so to
        // avoid blowing up the tone mapping code, strip/sanitize it
        params->color.sig_peak = 1.0;
    }

    if (params->chroma_location == MP_CHROMA_AUTO) {
        if (params->color.levels == MP_CSP_LEVELS_TV)
            params->chroma_location = MP_CHROMA_LEFT;
        if (params->color.levels == MP_CSP_LEVELS_PC)
            params->chroma_location = MP_CHROMA_CENTER;
    }

    if (params->color.light == MP_CSP_LIGHT_AUTO) {
        // HLG is always scene-referred (using its own OOTF), everything else
        // we assume is display-refered by default.
        if (params->color.gamma == MP_CSP_TRC_HLG) {
            params->color.light = MP_CSP_LIGHT_SCENE_HLG;
        } else {
            params->color.light = MP_CSP_LIGHT_DISPLAY;
        }
    }
}