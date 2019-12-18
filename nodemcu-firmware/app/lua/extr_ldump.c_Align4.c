#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wrote; scalar_t__ status; } ;
typedef  TYPE_1__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpChar (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void Align4(DumpState *D)
{
 while(D->wrote&3 && D->status==0)
  DumpChar(0,D);
}