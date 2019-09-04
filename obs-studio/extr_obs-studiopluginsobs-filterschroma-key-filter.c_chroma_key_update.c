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
struct chroma_key_filter_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  chroma_settings_update (struct chroma_key_filter_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  color_settings_update (struct chroma_key_filter_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chroma_key_update(void *data, obs_data_t *settings)
{
	struct chroma_key_filter_data *filter = data;

	color_settings_update(filter, settings);
	chroma_settings_update(filter, settings);
}