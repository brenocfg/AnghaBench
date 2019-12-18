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
typedef  int /*<<< orphan*/  nsICommandParams ;
typedef  int /*<<< orphan*/  HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  NSCMD_FONTFACE ; 
 int /*<<< orphan*/  NSSTATE_ATTRIBUTE ; 
 int /*<<< orphan*/ * create_nscommand_params () ; 
 int /*<<< orphan*/  do_ns_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_SetCStringValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void set_ns_fontname(HTMLDocument *This, const char *fontname)
{
    nsICommandParams *nsparam = create_nscommand_params();

    nsICommandParams_SetCStringValue(nsparam, NSSTATE_ATTRIBUTE, fontname);
    do_ns_command(This, NSCMD_FONTFACE, nsparam);
    nsICommandParams_Release(nsparam);
}