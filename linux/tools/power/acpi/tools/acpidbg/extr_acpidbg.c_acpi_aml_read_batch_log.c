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
struct circ_buf {char* buf; size_t head; } ;

/* Variables and functions */
 int ACPI_AML_BUF_SIZE ; 
#define  ACPI_AML_LOG_START 130 
 int ACPI_AML_LOG_STOP ; 
 int ACPI_AML_PROMPT_ROLL ; 
#define  ACPI_AML_PROMPT_START 129 
#define  ACPI_AML_PROMPT_STOP 128 
 char ACPI_DEBUGGER_COMMAND_PROMPT ; 
 char ACPI_DEBUGGER_EXECUTE_PROMPT ; 
 char acpi_aml_batch_prompt ; 
 char acpi_aml_batch_roll ; 
 int acpi_aml_exit ; 
 int acpi_aml_log_state ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int circ_space_to_end (struct circ_buf*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int acpi_aml_read_batch_log(int fd, struct circ_buf *crc)
{
	char *p;
	int len;
	int ret = 0;

	p = &crc->buf[crc->head];
	len = circ_space_to_end(crc);
	while (ret < len && acpi_aml_log_state != ACPI_AML_LOG_STOP) {
		if (acpi_aml_log_state == ACPI_AML_PROMPT_ROLL) {
			*p = acpi_aml_batch_roll;
			len = 1;
			crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
			ret += 1;
			acpi_aml_log_state = ACPI_AML_LOG_START;
		} else {
			len = read(fd, p, 1);
			if (len <= 0) {
				if (len < 0)
					perror("read");
				ret = len;
				break;
			}
		}
		switch (acpi_aml_log_state) {
		case ACPI_AML_LOG_START:
			if (*p == '\n')
				acpi_aml_log_state = ACPI_AML_PROMPT_START;
			crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
			ret += 1;
			break;
		case ACPI_AML_PROMPT_START:
			if (*p == ACPI_DEBUGGER_COMMAND_PROMPT ||
			    *p == ACPI_DEBUGGER_EXECUTE_PROMPT) {
				acpi_aml_batch_prompt = *p;
				acpi_aml_log_state = ACPI_AML_PROMPT_STOP;
			} else {
				if (*p != '\n')
					acpi_aml_log_state = ACPI_AML_LOG_START;
				crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
				ret += 1;
			}
			break;
		case ACPI_AML_PROMPT_STOP:
			if (*p == ' ') {
				acpi_aml_log_state = ACPI_AML_LOG_STOP;
				acpi_aml_exit = true;
			} else {
				/* Roll back */
				acpi_aml_log_state = ACPI_AML_PROMPT_ROLL;
				acpi_aml_batch_roll = *p;
				*p = acpi_aml_batch_prompt;
				crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
				ret += 1;
			}
			break;
		default:
			assert(0);
			break;
		}
	}
	return ret;
}