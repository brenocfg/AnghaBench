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
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * oss ; 

__attribute__((used)) static LRESULT WAVEMAP_drvClose(DWORD_PTR dwDevID)
{
    TRACE("(%08lx)\n", dwDevID);

    if (oss) {
	oss = NULL;
	return 1;
    }
    return 0;
}