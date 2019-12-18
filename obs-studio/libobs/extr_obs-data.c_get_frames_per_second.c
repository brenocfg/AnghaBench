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
typedef  void* uint32_t ;
struct obs_data_item {int dummy; } ;
struct media_frames_per_second {void* denominator; void* numerator; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ CLAMP (long long,int /*<<< orphan*/ ,long long) ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ get_option (int /*<<< orphan*/ *,char const**) ; 
 int media_frames_per_second_is_valid (struct media_frames_per_second) ; 
 struct obs_data_item* obs_data_item_byname (int /*<<< orphan*/ *,char*) ; 
 long long obs_data_item_get_int (struct obs_data_item*) ; 
 int /*<<< orphan*/  obs_data_item_release (struct obs_data_item**) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool get_frames_per_second(obs_data_t *data,
					 struct media_frames_per_second *fps,
					 const char **option)
{
	if (!data)
		return false;

	if (get_option(data, option))
		return true;

	if (!fps)
		goto free;

	struct obs_data_item *num = obs_data_item_byname(data, "numerator");
	struct obs_data_item *den = obs_data_item_byname(data, "denominator");
	if (!num || !den) {
		obs_data_item_release(&num);
		obs_data_item_release(&den);
		goto free;
	}

	long long num_ll = obs_data_item_get_int(num);
	long long den_ll = obs_data_item_get_int(den);

	fps->numerator = (uint32_t)CLAMP(num_ll, 0, (long long)UINT32_MAX);
	fps->denominator = (uint32_t)CLAMP(den_ll, 0, (long long)UINT32_MAX);

	obs_data_item_release(&num);
	obs_data_item_release(&den);

	obs_data_release(data);

	return media_frames_per_second_is_valid(*fps);

free:
	obs_data_release(data);
	return false;
}