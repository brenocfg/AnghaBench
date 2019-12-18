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
#define  HTTP_RESP_BAD_REQUEST 134 
#define  HTTP_RESP_FORBIDDEN 133 
#define  HTTP_RESP_MOVED_PERM 132 
#define  HTTP_RESP_NOT_FOUND 131 
#define  HTTP_RESP_OK 130 
#define  HTTP_RESP_PRECOND_FAIL 129 
#define  HTTP_RESP_REDIR_TEMP 128 

const char *web_response_code_to_string(int code) {
    switch(code) {
        case HTTP_RESP_OK:
            return "OK";

        case HTTP_RESP_MOVED_PERM:
            return "Moved Permanently";

        case HTTP_RESP_REDIR_TEMP:
            return "Temporary Redirect";

        case HTTP_RESP_BAD_REQUEST:
            return "Bad Request";

        case HTTP_RESP_FORBIDDEN:
            return "Forbidden";

        case HTTP_RESP_NOT_FOUND:
            return "Not Found";

        case HTTP_RESP_PRECOND_FAIL:
            return "Preconditions Failed";

        default:
            if(code >= 100 && code < 200)
                return "Informational";

            if(code >= 200 && code < 300)
                return "Successful";

            if(code >= 300 && code < 400)
                return "Redirection";

            if(code >= 400 && code < 500)
                return "Bad Request";

            if(code >= 500 && code < 600)
                return "Server Error";

            return "Undefined Error";
    }
}