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
struct threads {int dummy; } ;
struct machine {struct threads* threads; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 unsigned int THREADS__TABLE_SIZE ; 

__attribute__((used)) static inline struct threads *machine__threads(struct machine *machine, pid_t tid)
{
	/* Cast it to handle tid == -1 */
	return &machine->threads[(unsigned int)tid % THREADS__TABLE_SIZE];
}