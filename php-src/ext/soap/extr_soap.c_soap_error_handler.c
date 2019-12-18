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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 int /*<<< orphan*/  SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_old_error_handler (int,char const*,int /*<<< orphan*/  const,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_real_error_handler (int,char const*,int /*<<< orphan*/  const,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_soap_error_handler ; 

__attribute__((used)) static void soap_error_handler(int error_num, const char *error_filename, const uint32_t error_lineno, const char *format, va_list args) /* {{{ */
{
	if (EXPECTED(!SOAP_GLOBAL(use_soap_error_handler))) {
		call_old_error_handler(error_num, error_filename, error_lineno, format, args);
	} else {
		soap_real_error_handler(error_num, error_filename, error_lineno, format, args);
	}
}