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

const char *web_response_code_to_string(int code) {
    switch(code) {
        case 200:
            return "OK";

        case 307:
            return "Temporary Redirect";

        case 400:
            return "Bad Request";

        case 403:
            return "Forbidden";

        case 404:
            return "Not Found";

        case 412:
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