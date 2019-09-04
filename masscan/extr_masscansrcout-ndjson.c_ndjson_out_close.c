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
struct Output {int dummy; } ;
typedef  struct Output FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 

__attribute__((used)) static void
ndjson_out_close(struct Output *out, FILE *fp)
{
    UNUSEDPARM(out);
    UNUSEDPARM(fp); 
}