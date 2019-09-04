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
struct session_data {int fedai_id; } ;
struct msm_routing_data {struct session_data* sessions; } ;

/* Variables and functions */
 int MAX_SESSIONS ; 

__attribute__((used)) static struct session_data *get_session_from_id(struct msm_routing_data *data,
						int fedai_id)
{
	int i;

	for (i = 0; i < MAX_SESSIONS; i++) {
		if (fedai_id == data->sessions[i].fedai_id)
			return &data->sessions[i];
	}

	return NULL;
}