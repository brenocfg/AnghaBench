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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/ * engine_table_select (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pkey_asn1_meth_table ; 

ENGINE *ENGINE_get_pkey_asn1_meth_engine(int nid)
{
    return engine_table_select(&pkey_asn1_meth_table, nid);
}