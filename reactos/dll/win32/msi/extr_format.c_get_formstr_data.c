#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * deformatted; } ;
struct TYPE_5__ {size_t n; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  TYPE_1__ FORMSTR ;
typedef  TYPE_2__ FORMAT ;

/* Variables and functions */

__attribute__((used)) static LPCWSTR get_formstr_data(FORMAT *format, FORMSTR *str)
{
    return &format->deformatted[str->n];
}