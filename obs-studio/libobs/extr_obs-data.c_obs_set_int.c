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
struct obs_data_number {long long int_val; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  (* set_item_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,struct obs_data_number*,int,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_DATA_NUMBER ; 
 int /*<<< orphan*/  OBS_DATA_NUM_INT ; 

__attribute__((used)) static inline void obs_set_int(obs_data_t *data, obs_data_item_t **item,
			       const char *name, long long val,
			       set_item_t set_item_)
{
	struct obs_data_number num;
	num.type = OBS_DATA_NUM_INT;
	num.int_val = val;
	set_item_(data, item, name, &num, sizeof(struct obs_data_number),
		  OBS_DATA_NUMBER);
}