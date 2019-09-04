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
struct rtmp_stream {int /*<<< orphan*/  send_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ os_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool reset_semaphore(struct rtmp_stream *stream)
{
	os_sem_destroy(stream->send_sem);
	return os_sem_init(&stream->send_sem, 0) == 0;
}