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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct mutex {int dummy; } ;
struct kfifo {int dummy; } ;
typedef  int /*<<< orphan*/  latency ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ kfifo_len (struct kfifo*) ; 
 int kfifo_out (struct kfifo*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_loopback_dbgfs_latency_show_common(struct seq_file *s,
						 struct kfifo *kfifo,
						 struct mutex *mutex)
{
	u32 latency;
	int retval;

	if (kfifo_len(kfifo) == 0) {
		retval = -EAGAIN;
		goto done;
	}

	mutex_lock(mutex);
	retval = kfifo_out(kfifo, &latency, sizeof(latency));
	if (retval > 0) {
		seq_printf(s, "%u", latency);
		retval = 0;
	}
	mutex_unlock(mutex);
done:
	return retval;
}