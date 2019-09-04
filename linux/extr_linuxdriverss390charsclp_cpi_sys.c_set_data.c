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
 int /*<<< orphan*/  CPI_LENGTH_NAME ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclp_ascebc_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void set_data(char *field, char *data)
{
	memset(field, ' ', CPI_LENGTH_NAME);
	memcpy(field, data, strlen(data));
	sclp_ascebc_str(field, CPI_LENGTH_NAME);
}