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
typedef  int /*<<< orphan*/  gdIOCtx ;
typedef  int /*<<< orphan*/  LZW_STATIC_DATA ;

/* Variables and functions */
 int LWZReadByte_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,int,int*) ; 
 scalar_t__ VERBOSE ; 
 int /*<<< orphan*/  printf (char*,char,int,int) ; 

__attribute__((used)) static int
LWZReadByte(gdIOCtx *fd, LZW_STATIC_DATA *sd, char flag, int input_code_size, int *ZeroDataBlockP)
{
	int rv;

 rv = LWZReadByte_(fd, sd, flag, input_code_size, ZeroDataBlockP);
 if (VERBOSE) printf("[LWZReadByte(,%d,%d) returning %d]\n",flag,input_code_size,rv);
	return(rv);
}