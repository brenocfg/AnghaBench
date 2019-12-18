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
typedef  int /*<<< orphan*/  EC_METHOD ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_GROUP_new_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

EC_GROUP *EC_GROUP_new(const EC_METHOD *meth)
{
    return EC_GROUP_new_ex(NULL, meth);
}