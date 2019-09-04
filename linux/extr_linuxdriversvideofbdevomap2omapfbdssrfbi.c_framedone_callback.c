#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void (* framedone_callback ) (void*) ;void* framedone_callback_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 TYPE_1__ rfbi ; 

__attribute__((used)) static void framedone_callback(void *data)
{
	void (*callback)(void *data);

	DSSDBG("FRAMEDONE\n");

	REG_FLD_MOD(RFBI_CONTROL, 0, 0, 0);

	callback = rfbi.framedone_callback;
	rfbi.framedone_callback = NULL;

	if (callback != NULL)
		callback(rfbi.framedone_callback_data);
}