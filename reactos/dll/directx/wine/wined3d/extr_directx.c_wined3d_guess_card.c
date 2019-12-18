#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shader_caps {int dummy; } ;
struct fragment_caps {int dummy; } ;
typedef  enum wined3d_pci_vendor { ____Placeholder_wined3d_pci_vendor } wined3d_pci_vendor ;
typedef  enum wined3d_pci_device { ____Placeholder_wined3d_pci_device } wined3d_pci_device ;
typedef  enum wined3d_gl_vendor { ____Placeholder_wined3d_gl_vendor } wined3d_gl_vendor ;
typedef  enum wined3d_d3d_level { ____Placeholder_wined3d_d3d_level } wined3d_d3d_level ;
struct TYPE_3__ {int card_vendor; int* card_fallback; int /*<<< orphan*/  gl_vendor_count; int /*<<< orphan*/  gl_vendor_selection; int /*<<< orphan*/  description; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ) ; 
 int HW_VENDOR_NVIDIA ; 
 int PCI_DEVICE_NONE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int* card_fallback_nvidia ; 
 TYPE_1__* card_vendor_table ; 
 int d3d_level_from_caps (struct shader_caps const*,struct fragment_caps const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int select_card_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static enum wined3d_pci_device wined3d_guess_card(const struct shader_caps *shader_caps, const struct fragment_caps *fragment_caps,
        DWORD glsl_version, const char *gl_renderer, enum wined3d_gl_vendor *gl_vendor, enum wined3d_pci_vendor *card_vendor)
{
    /* A Direct3D device object contains the PCI id (vendor + device) of the
     * videocard which is used for rendering. Various applications use this
     * information to get a rough estimation of the features of the card and
     * some might use it for enabling 3d effects only on certain types of
     * videocards. In some cases games might even use it to work around bugs
     * which happen on certain videocards/driver combinations. The problem is
     * that OpenGL only exposes a rendering string containing the name of the
     * videocard and not the PCI id.
     *
     * Various games depend on the PCI id, so somehow we need to provide one.
     * A simple option is to parse the renderer string and translate this to
     * the right PCI id. This is a lot of work because there are more than 200
     * GPUs just for Nvidia. Various cards share the same renderer string, so
     * the amount of code might be 'small' but there are quite a number of
     * exceptions which would make this a pain to maintain. Another way would
     * be to query the PCI id from the operating system (assuming this is the
     * videocard which is used for rendering which is not always the case).
     * This would work but it is not very portable. Second it would not work
     * well in, let's say, a remote X situation in which the amount of 3d
     * features which can be used is limited.
     *
     * As said most games only use the PCI id to get an indication of the
     * capabilities of the card. It doesn't really matter if the given id is
     * the correct one if we return the id of a card with similar 3d features.
     *
     * The code below checks the OpenGL capabilities of a videocard and matches
     * that to a certain level of Direct3D functionality. Once a card passes
     * the Direct3D9 check, we know that the card (in case of Nvidia) is at
     * least a GeforceFX. To give a better estimate we do a basic check on the
     * renderer string but if that won't pass we return a default card. This
     * way is better than maintaining a full card database as even without a
     * full database we can return a card with similar features. Second the
     * size of the database can be made quite small because when you know what
     * type of 3d functionality a card has, you know to which GPU family the
     * GPU must belong. Because of this you only have to check a small part of
     * the renderer string to distinguish between different models from that
     * family.
     *
     * The code also selects a default amount of video memory which we will
     * use for an estimation of the amount of free texture memory. In case of
     * real D3D the amount of texture memory includes video memory and system
     * memory (to be specific AGP memory or in case of PCIE TurboCache /
     * HyperMemory). We don't know how much system memory can be addressed by
     * the system but we can make a reasonable estimation about the amount of
     * video memory. If the value is slightly wrong it doesn't matter as we
     * didn't include AGP-like memory which makes the amount of addressable
     * memory higher and second OpenGL isn't that critical it moves to system
     * memory behind our backs if really needed. Note that the amount of video
     * memory can be overruled using a registry setting. */

    unsigned int i;
    enum wined3d_d3d_level d3d_level = d3d_level_from_caps(shader_caps, fragment_caps, glsl_version);
    enum wined3d_pci_device device;

    for (i = 0; i < ARRAY_SIZE(card_vendor_table); ++i)
    {
        if (card_vendor_table[i].card_vendor != *card_vendor)
            continue;

        TRACE("Applying card selector \"%s\".\n", card_vendor_table[i].description);
        device = select_card_handler(card_vendor_table[i].gl_vendor_selection,
                card_vendor_table[i].gl_vendor_count, *gl_vendor, gl_renderer);
        if (device != PCI_DEVICE_NONE)
            return device;

        TRACE("Unrecognized renderer %s, falling back to default.\n", debugstr_a(gl_renderer));
        return card_vendor_table[i].card_fallback[d3d_level];
    }

    FIXME("No card selector available for card vendor %04x (using GL_RENDERER %s).\n",
            *card_vendor, debugstr_a(gl_renderer));

    /* Default to generic Nvidia hardware based on the supported OpenGL extensions. */
    *card_vendor = HW_VENDOR_NVIDIA;
    return card_fallback_nvidia[d3d_level];
}