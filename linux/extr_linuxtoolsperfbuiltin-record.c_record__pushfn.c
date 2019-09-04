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
struct record {int /*<<< orphan*/  samples; } ;

/* Variables and functions */
 int record__write (struct record*,void*,size_t) ; 

__attribute__((used)) static int record__pushfn(void *to, void *bf, size_t size)
{
	struct record *rec = to;

	rec->samples++;
	return record__write(rec, bf, size);
}