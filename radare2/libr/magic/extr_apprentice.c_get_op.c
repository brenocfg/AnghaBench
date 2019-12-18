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

/* Variables and functions */
 int FILE_OPADD ; 
 int FILE_OPAND ; 
 int FILE_OPDIVIDE ; 
 int FILE_OPMINUS ; 
 int FILE_OPMODULO ; 
 int FILE_OPMULTIPLY ; 
 int FILE_OPOR ; 
 int FILE_OPXOR ; 

__attribute__((used)) static int get_op(char c) {
	switch (c) {
	case '&': return FILE_OPAND;
	case '|': return FILE_OPOR;
	case '^': return FILE_OPXOR;
	case '+': return FILE_OPADD;
	case '-': return FILE_OPMINUS;
	case '*': return FILE_OPMULTIPLY;
	case '/': return FILE_OPDIVIDE;
	case '%': return FILE_OPMODULO;
	default:  return -1;
	}
}