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
 int /*<<< orphan*/  ACPI_OPTION (char*,char*) ; 
 int /*<<< orphan*/  ACPI_USAGE_HEADER (char*) ; 
 int /*<<< orphan*/  ACPI_USAGE_TEXT (char*) ; 

__attribute__((used)) static void ap_display_usage(void)
{

	ACPI_USAGE_HEADER("acpidump [options]");

	ACPI_OPTION("-b", "Dump tables to binary files");
	ACPI_OPTION("-h -?", "This help message");
	ACPI_OPTION("-o <File>", "Redirect output to file");
	ACPI_OPTION("-r <Address>", "Dump tables from specified RSDP");
	ACPI_OPTION("-s", "Print table summaries only");
	ACPI_OPTION("-v", "Display version information");
	ACPI_OPTION("-vd", "Display build date and time");
	ACPI_OPTION("-z", "Verbose mode");

	ACPI_USAGE_TEXT("\nTable Options:\n");

	ACPI_OPTION("-a <Address>", "Get table via a physical address");
	ACPI_OPTION("-c <on|off>", "Turning on/off customized table dumping");
	ACPI_OPTION("-f <BinaryFile>", "Get table via a binary file");
	ACPI_OPTION("-n <Signature>", "Get table via a name/signature");
	ACPI_OPTION("-x", "Do not use but dump XSDT");
	ACPI_OPTION("-x -x", "Do not use or dump XSDT");

	ACPI_USAGE_TEXT("\n"
			"Invocation without parameters dumps all available tables\n"
			"Multiple mixed instances of -a, -f, and -n are supported\n\n");
}