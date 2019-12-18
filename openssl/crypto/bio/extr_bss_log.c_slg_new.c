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
struct TYPE_4__ {int init; int /*<<< orphan*/ * ptr; scalar_t__ num; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  xopenlog (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slg_new(BIO *bi)
{
    bi->init = 1;
    bi->num = 0;
    bi->ptr = NULL;
    xopenlog(bi, "application", LOG_DAEMON);
    return 1;
}