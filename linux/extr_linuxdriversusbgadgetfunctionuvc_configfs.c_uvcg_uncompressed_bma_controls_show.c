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
struct uvcg_uncompressed {int /*<<< orphan*/  fmt; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct uvcg_uncompressed* to_uvcg_uncompressed (struct config_item*) ; 
 int /*<<< orphan*/  uvcg_format_bma_controls_show (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline ssize_t
uvcg_uncompressed_bma_controls_show(struct config_item *item, char *page)
{
	struct uvcg_uncompressed *unc = to_uvcg_uncompressed(item);
	return uvcg_format_bma_controls_show(&unc->fmt, page);
}