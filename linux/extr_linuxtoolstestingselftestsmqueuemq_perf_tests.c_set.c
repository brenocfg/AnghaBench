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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 void shutdown (int,char*,int) ; 

__attribute__((used)) static inline void set(FILE *stream, int value)
{
	int new_value;

	rewind(stream);
	if (fprintf(stream, "%d", value) < 0)
		return shutdown(5, "Failed writing to /proc file", __LINE__);
	new_value = get(stream);
	if (new_value != value)
		return shutdown(5, "We didn't get what we wrote to /proc back",
				__LINE__);
}