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
 int /*<<< orphan*/  ERR_LIB_CMP ; 
 int ERR_TXT_STRING ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char const*,char const*) ; 
 unsigned long ERR_peek_last_error () ; 
 int /*<<< orphan*/  ERR_peek_last_error_all (char const**,int*,char const**,char const**,int*) ; 
 size_t MAX_DATA_LEN ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strndup (char const*,int) ; 
 int /*<<< orphan*/  put_error (int /*<<< orphan*/ ,char const*,unsigned long,char const*,int) ; 
 size_t strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

void ossl_cmp_add_error_txt(const char *separator, const char *txt)
{
    const char *file = NULL;
    int line;
    const char *func = NULL;
    const char *data = NULL;
    int flags;
    unsigned long err = ERR_peek_last_error();

    if (separator == NULL)
        separator = "";
    if (err == 0)
        put_error(ERR_LIB_CMP, NULL, 0, "", 0);

    do {
        size_t available_len, data_len;
        const char *curr = txt, *next = txt;
        char *tmp;

        ERR_peek_last_error_all(&file, &line, &func, &data, &flags);
        if ((flags & ERR_TXT_STRING) == 0) {
            data = "";
            separator = "";
        }
        data_len = strlen(data);

        /* workaround for limit of ERR_print_errors_cb() */
        if (data_len >= MAX_DATA_LEN
                || strlen(separator) >= (size_t)(MAX_DATA_LEN - data_len))
            available_len = 0;
        else
            available_len = MAX_DATA_LEN - data_len - strlen(separator) - 1;
        /* MAX_DATA_LEN > available_len >= 0 */

        if (separator[0] == '\0') {
            const size_t len_next = strlen(next);

            if (len_next <= available_len) {
                next += len_next;
                curr = NULL; /* no need to split */
            }
            else {
                next += available_len;
                curr = next; /* will split at this point */
            }
        } else {
            while (*next != '\0' && (size_t)(next - txt) <= available_len) {
                curr = next;
                next = strstr(curr, separator);
                if (next != NULL)
                    next += strlen(separator);
                else
                    next = curr + strlen(curr);
            }
            if ((size_t)(next - txt) <= available_len)
                curr = NULL; /* the above loop implies *next == '\0' */
        }
        if (curr != NULL) {
            /* split error msg at curr since error data would get too long */
            if (curr != txt) {
                tmp = OPENSSL_strndup(txt, curr - txt);
                if (tmp == NULL)
                    return;
                ERR_add_error_data(2, separator, tmp);
                OPENSSL_free(tmp);
            }
            put_error(ERR_LIB_CMP, func, err, file, line);
            txt = curr;
        } else {
            ERR_add_error_data(2, separator, txt);
            txt = next; /* finished */
        }
    } while (*txt != '\0');
}