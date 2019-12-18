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
struct tcp_pcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERROR_VOID (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_NONFATAL ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_UNKOWN_ERROR ; 
 int /*<<< orphan*/  LITLEN (int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int enduser_setup_http_handle_credentials (char*,int) ; 
 int /*<<< orphan*/  enduser_setup_http_serve_header (struct tcp_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enduser_setup_write_file_with_extra_configuration_data (char*,int) ; 
 int /*<<< orphan*/  http_header_302_trying ; 
 int /*<<< orphan*/  http_header_400 ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void enduser_setup_handle_POST(struct tcp_pcb *http_client, char* data, size_t data_len)
{
    ENDUSER_SETUP_DEBUG("Handling POST");
    if (strncmp(data + 5, "/setwifi ", 9) == 0) // User clicked the submit button
    {
      char* body=strstr(data, "\r\n\r\n");
      char *content_length_str = strstr(data, "Content-Length: ");
      if( body == NULL || content_length_str == NULL)
      {
        enduser_setup_http_serve_header(http_client, http_header_400, LITLEN(http_header_400));
        return;
      }
      int bodylength = atoi(content_length_str + 16);
      body += 4; // length of the double CRLF found above
      switch (enduser_setup_http_handle_credentials(body, bodylength))
      {
        case 0: {
          // all went fine, extract all the form data into a file
            enduser_setup_write_file_with_extra_configuration_data(body, bodylength);
          // redirect user to the base page with the trying flag
          enduser_setup_http_serve_header(http_client, http_header_302_trying, LITLEN(http_header_302_trying));
          break;
        }
        case 1:
          enduser_setup_http_serve_header(http_client, http_header_400, LITLEN(http_header_400));
          break;
        default:
          ENDUSER_SETUP_ERROR_VOID("http_recvcb failed. Failed to handle wifi credentials.", ENDUSER_SETUP_ERR_UNKOWN_ERROR, ENDUSER_SETUP_ERR_NONFATAL);
          break;
      }
    }
}