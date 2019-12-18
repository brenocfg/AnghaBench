#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sts; } ;
struct TYPE_4__ {char* name; } ;
typedef  TYPE_2__ SharedTuplestoreAccessor ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPGPATH ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void
sts_filename(char *name, SharedTuplestoreAccessor *accessor, int participant)
{
	snprintf(name, MAXPGPATH, "%s.p%d", accessor->sts->name, participant);
}