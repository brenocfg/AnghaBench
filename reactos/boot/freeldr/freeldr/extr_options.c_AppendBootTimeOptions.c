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
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 scalar_t__ BootLogging ; 
 int BootOptionChoice ; 
#define  DIRECTORY_SERVICES_RESTORE_MODE 132 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 scalar_t__ DebuggingMode ; 
#define  LAST_KNOWN_GOOD_CONFIGURATION 131 
#define  SAFE_MODE 130 
#define  SAFE_MODE_WITH_COMMAND_PROMPT 129 
#define  SAFE_MODE_WITH_NETWORKING 128 
 scalar_t__ VgaMode ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 

VOID AppendBootTimeOptions(PCHAR BootOptions)
{
    switch (BootOptionChoice)
    {
        case SAFE_MODE:
            strcat(BootOptions, " /SAFEBOOT:MINIMAL /SOS /NOGUIBOOT");
            break;

        case SAFE_MODE_WITH_NETWORKING:
            strcat(BootOptions, " /SAFEBOOT:NETWORK /SOS /NOGUIBOOT");
            break;

        case SAFE_MODE_WITH_COMMAND_PROMPT:
            strcat(BootOptions, " /SAFEBOOT:MINIMAL(ALTERNATESHELL) /SOS /NOGUIBOOT");
            break;

        case LAST_KNOWN_GOOD_CONFIGURATION:
            DbgPrint("Last known good configuration is not supported yet!\n");
            break;

        case DIRECTORY_SERVICES_RESTORE_MODE:
            strcat(BootOptions, " /SAFEBOOT:DSREPAIR /SOS");
            break;

        default:
            break;
    }

    if (BootLogging)
        strcat(BootOptions, " /BOOTLOG");

    if (VgaMode)
        strcat(BootOptions, " /BASEVIDEO");

    if (DebuggingMode)
        strcat(BootOptions, " /DEBUG");
}