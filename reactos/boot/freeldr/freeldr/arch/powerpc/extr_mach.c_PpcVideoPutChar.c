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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,int) ; 

VOID PpcVideoPutChar( int Ch, UCHAR Attr, unsigned X, unsigned Y ) {
    printf( "\033[%d;%dH%c", Y, X, Ch );
}