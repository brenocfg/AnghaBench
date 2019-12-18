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
struct TYPE_4__ {scalar_t__ Context; } ;
struct TYPE_5__ {TYPE_1__ For; } ;
typedef  TYPE_2__ PARSED_COMMAND ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ bCtrlBreak ; 
 scalar_t__ fc ; 

__attribute__((used)) static BOOL Exiting(PARSED_COMMAND *Cmd)
{
    /* Someone might have removed our context */
    return bCtrlBreak || fc != Cmd->For.Context;
}