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
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  PRUnichar ;

/* Variables and functions */
 int /*<<< orphan*/  NS_StringGetData (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

UINT32 nsAString_GetData(const nsAString *str, const PRUnichar **data)
{
    return NS_StringGetData(str, data, NULL);
}