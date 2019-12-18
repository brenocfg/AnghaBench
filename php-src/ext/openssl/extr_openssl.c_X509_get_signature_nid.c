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
struct TYPE_5__ {TYPE_1__* sig_alg; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;

/* Variables and functions */
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int X509_get_signature_nid(const X509 *x)
{
	return OBJ_obj2nid(x->sig_alg->algorithm);
}