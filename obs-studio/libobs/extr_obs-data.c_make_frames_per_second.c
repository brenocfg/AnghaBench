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
struct media_frames_per_second {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_set_double (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static inline obs_data_t *
make_frames_per_second(struct media_frames_per_second fps, const char *option)
{
	obs_data_t *obj = obs_data_create();

	if (!option) {
		obs_data_set_double(obj, "numerator", fps.numerator);
		obs_data_set_double(obj, "denominator", fps.denominator);

	} else {
		obs_data_set_string(obj, "option", option);
	}

	return obj;
}