#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uchar ;
struct TYPE_3__ {char* val; scalar_t__ key; } ;
typedef  TYPE_1__ kv ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char,char*) ; 

__attribute__((used)) static void printkv(kv *kvarr, FILE *fp, uchar max)
{
	uchar i = 0;

	for (; i < max && kvarr[i].key; ++i)
		fprintf(fp, " %c: %s\n", (char)kvarr[i].key, kvarr[i].val);
}