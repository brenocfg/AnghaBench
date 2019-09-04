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
struct snd_sb_csp {int /*<<< orphan*/  access_mutex; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sb_csp_unuse(struct snd_sb_csp * p)
{
	mutex_lock(&p->access_mutex);
	p->used--;
	mutex_unlock(&p->access_mutex);

	return 0;
}