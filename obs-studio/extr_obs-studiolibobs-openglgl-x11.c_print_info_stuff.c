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
struct gs_init_data {int /*<<< orphan*/  adapter; int /*<<< orphan*/  zsformat; int /*<<< orphan*/  format; int /*<<< orphan*/  num_backbuffers; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_info_stuff(const struct gs_init_data *info)
{
	blog(	LOG_INFO,
		"X and Y: %i %i\n"
		"Backbuffers: %i\n"
		"Color Format: %i\n"
		"ZStencil Format: %i\n"
		"Adapter: %i\n",
		info->cx, info->cy,
		info->num_backbuffers,
		info->format, info->zsformat,
		info->adapter
	);
}