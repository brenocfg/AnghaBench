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
struct TYPE_5__ {int /*<<< orphan*/  quoted; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ HbaToken ;

/* Variables and functions */
 TYPE_1__* make_hba_token (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HbaToken *
copy_hba_token(HbaToken *in)
{
	HbaToken   *out = make_hba_token(in->string, in->quoted);

	return out;
}