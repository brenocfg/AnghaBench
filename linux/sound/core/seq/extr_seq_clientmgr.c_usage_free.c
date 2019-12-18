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
struct snd_seq_usage {int cur; } ;

/* Variables and functions */

__attribute__((used)) static void usage_free(struct snd_seq_usage *res, int num)
{
	res->cur -= num;
}