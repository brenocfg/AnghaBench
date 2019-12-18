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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* test_mk_file_path (char const*,char const*) ; 

__attribute__((used)) static int read_text_file(const char *dir, const char *file,
                          char *buffer, int buffer_length)
{
    int len = -1;
    char *file_path = test_mk_file_path(dir, file);

    if (file_path != NULL) {
        BIO *file_io = BIO_new_file(file_path, "r");

        if (file_io != NULL)
            len = BIO_read(file_io, buffer, buffer_length);
        BIO_free(file_io);
    }

    OPENSSL_free(file_path);
    return len;
}