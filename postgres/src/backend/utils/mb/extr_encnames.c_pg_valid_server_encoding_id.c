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
 int PG_VALID_BE_ENCODING (int) ; 

int
pg_valid_server_encoding_id(int encoding)
{
	return PG_VALID_BE_ENCODING(encoding);
}