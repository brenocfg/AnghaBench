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
typedef  int /*<<< orphan*/  uint64_t ;
struct obs_output {int /*<<< orphan*/  delay_mutex; int /*<<< orphan*/  delay_data; } ;
struct encoder_packet {int dummy; } ;
struct delay_data {int /*<<< orphan*/  packet; int /*<<< orphan*/  ts; int /*<<< orphan*/  msg; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  dd ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_MSG_PACKET ; 
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,struct delay_data*,int) ; 
 int /*<<< orphan*/  obs_encoder_packet_create_instance (int /*<<< orphan*/ *,struct encoder_packet*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void push_packet(struct obs_output *output,
			       struct encoder_packet *packet, uint64_t t)
{
	struct delay_data dd = {0};

	dd.msg = DELAY_MSG_PACKET;
	dd.ts = t;
	obs_encoder_packet_create_instance(&dd.packet, packet);

	pthread_mutex_lock(&output->delay_mutex);
	circlebuf_push_back(&output->delay_data, &dd, sizeof(dd));
	pthread_mutex_unlock(&output->delay_mutex);
}