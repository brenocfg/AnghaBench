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
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown (int,char*,int) ; 

__attribute__((used)) static inline int get(FILE *stream)
{
	int value;
	rewind(stream);
	if (fscanf(stream, "%d", &value) != 1)
		shutdown(4, "Error reading /proc entry", __LINE__ - 1);
	return value;
}