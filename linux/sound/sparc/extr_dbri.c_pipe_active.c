#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_dbri {TYPE_1__* pipes; } ;
struct TYPE_2__ {int desc; } ;

/* Variables and functions */

__attribute__((used)) static inline int pipe_active(struct snd_dbri *dbri, int pipe)
{
	return ((pipe >= 0) && (dbri->pipes[pipe].desc != -1));
}