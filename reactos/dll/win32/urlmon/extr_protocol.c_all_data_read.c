#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ALL_DATA_READ ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  report_data (TYPE_1__*) ; 
 int /*<<< orphan*/  report_result (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void all_data_read(Protocol *protocol)
{
    protocol->flags |= FLAG_ALL_DATA_READ;

    report_data(protocol);
    report_result(protocol, S_OK);
}