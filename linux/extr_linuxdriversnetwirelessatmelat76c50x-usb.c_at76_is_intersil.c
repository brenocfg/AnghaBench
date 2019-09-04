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
typedef  enum board_type { ____Placeholder_board_type } board_type ;

/* Variables and functions */
 int BOARD_503_ISL3861 ; 
 int BOARD_503_ISL3863 ; 

__attribute__((used)) static inline int at76_is_intersil(enum board_type board)
{
	return (board == BOARD_503_ISL3861 || board == BOARD_503_ISL3863);
}