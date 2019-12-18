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
typedef  int /*<<< orphan*/  text ;
typedef  scalar_t__ data ;

/* Variables and functions */
 scalar_t__ VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_to_ascii (unsigned char*,unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static text *
encode_to_ascii(text *data, int enc)
{
	pg_to_ascii((unsigned char *) VARDATA(data),	/* src */
				(unsigned char *) (data) + VARSIZE(data),	/* src end */
				(unsigned char *) VARDATA(data),	/* dest */
				enc);			/* encoding */

	return data;
}