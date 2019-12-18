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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HEADER_INFO ;

/* Variables and functions */
 scalar_t__ HEADER_IndexToOrder (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_OrderToIndex (int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static INT
HEADER_PrevItem(const HEADER_INFO *infoPtr, INT iItem)
{
    return HEADER_OrderToIndex(infoPtr, HEADER_IndexToOrder(infoPtr, iItem)-1);
}