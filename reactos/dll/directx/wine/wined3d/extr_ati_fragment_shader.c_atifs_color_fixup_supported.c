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
struct color_fixup_desc {int dummy; } ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  color_fixup_rg ; 
 int /*<<< orphan*/  color_fixup_rgba ; 
 int /*<<< orphan*/  color_fixup_rgl ; 
 scalar_t__ is_identity_fixup (struct color_fixup_desc) ; 
 scalar_t__ is_same_fixup (struct color_fixup_desc,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL atifs_color_fixup_supported(struct color_fixup_desc fixup)
{
    /* We only support sign fixup of the first two channels. */
    return is_identity_fixup(fixup) || is_same_fixup(fixup, color_fixup_rg)
            || is_same_fixup(fixup, color_fixup_rgl) || is_same_fixup(fixup, color_fixup_rgba);
}