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
 scalar_t__ valid_ujis (unsigned int const) ; 
 scalar_t__ valid_ujis_ss2 (unsigned int const) ; 
 scalar_t__ valid_ujis_ss3 (unsigned int const) ; 

__attribute__((used)) static unsigned int mysqlnd_mbcharlen_ujis(const unsigned int ujis)
{
	return (valid_ujis(ujis)? 2: valid_ujis_ss2(ujis)? 2: valid_ujis_ss3(ujis)? 3: 1);
}