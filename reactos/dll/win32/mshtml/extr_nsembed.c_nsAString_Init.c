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
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_StringContainerInit2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PR_UINT32_MAX ; 

BOOL nsAString_Init(nsAString *str, const PRUnichar *data)
{
    return NS_SUCCEEDED(NS_StringContainerInit2(str, data, PR_UINT32_MAX, 0));
}