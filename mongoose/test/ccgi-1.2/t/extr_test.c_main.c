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
typedef  int /*<<< orphan*/  CGI_varlist ;
typedef  int /*<<< orphan*/  CGI_value ;

/* Variables and functions */
 int /*<<< orphan*/ * CGI_add_var (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ CGI_decode_base64 (char*,int*) ; 
 scalar_t__ CGI_decode_hex (char*,int*) ; 
 int /*<<< orphan*/ * CGI_decode_query (int /*<<< orphan*/ ,char*) ; 
 char* CGI_decode_url (char*) ; 
 char* CGI_decrypt (char*,int*,char const*) ; 
 char* CGI_encode_base64 (char*,int) ; 
 char* CGI_encode_entity (char*) ; 
 char* CGI_encode_hex (char*,int) ; 
 char* CGI_encode_query (char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 char* CGI_encode_url (char*,char*) ; 
 char* CGI_encode_varlist (int /*<<< orphan*/ *,char*) ; 
 char* CGI_encrypt (char*,int,char const*) ; 
 int /*<<< orphan*/ * CGI_get_cookie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CGI_get_post (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * CGI_get_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CGI_lookup_all (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dumplist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

int
main(int argc, char **argv) {
    CGI_varlist *vl;
    char *p;
    CGI_value *value;
    int i;

    if (strcmp(argv[1], "CGI_get_cookie") == 0) {
        vl = CGI_get_cookie(0);
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "CGI_get_query") == 0) {
        vl = CGI_get_query(0);
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "CGI_decode_query") == 0) {
        vl = CGI_decode_query(0, argv[2]);
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "CGI_get_post") == 0) {
        vl = CGI_get_post(0, 0);
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "upload") == 0) {
        vl = CGI_get_post(0, "./cgi-upload-XXXXXX");
        value = CGI_lookup_all(vl, "upload");
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "CGI_add_var") == 0) {
        vl = 0;
        for (i = 2; i + 1 < argc; i += 2) {
            vl = CGI_add_var(vl, argv[i], argv[i + 1]);
        }
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "CGI_encode_varlist") == 0) {
        vl = 0;
        for (i = 2; i + 1 < argc; i += 2) {
            vl = CGI_add_var(vl, argv[i], argv[i + 1]);
        }
        dumplist(vl);
        p = CGI_encode_varlist(vl, ".-_");
        fputs(p, stdout);
        fputc('\n', stdout);
        return 0;
    }


    if (strcmp(argv[1], "CGI_encode_url") == 0) {
        p = CGI_encode_url(argv[2], ".-_");
        fputs(p, stdout);
        fputc('\n', stdout);
        p = CGI_decode_url(p);
        fputs(p, stdout);
        fputc('\n', stdout);
        return 0;
    }

    if (strcmp(argv[1], "CGI_encode_query") == 0) {
        p = CGI_encode_query(".-_", argv[2], argv[3], argv[4], argv[5],
            argv[6], argv[7], argv[8], argv[9], argv[10], argv[11],
            argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
            argv[18], argv[19], argv[20], argv[21], (char *)0);
        fputs(p, stdout);
        fputc('\n', stdout);
        vl = CGI_decode_query(0, p);
        dumplist(vl);
        return 0;
    }

    if (strcmp(argv[1], "CGI_encode_base64") == 0) {
        p = argv[2];
        p = CGI_encode_base64(p, strlen(p));
        fputs(p, stdout);
        fputc('\n', stdout);
        p = (char *) CGI_decode_base64(p, &i);
        fwrite(p, i, 1, stdout);
        fputc('\n', stdout);
        return 0;
    }

    if (strcmp(argv[1], "CGI_encode_hex") == 0) {
        p = argv[2];
        p = CGI_encode_hex(p, strlen(p));
        fputs(p, stdout);
        fputc('\n', stdout);
        p = (char *) CGI_decode_hex(p, &i);
        fwrite(p, i, 1, stdout);
        fputc('\n', stdout);
        return 0;
    }

    if (strcmp(argv[1], "CGI_encode_entity") == 0) {
        p = CGI_encode_entity(argv[2]);
        fputs(p, stdout);
        fputc('\n', stdout);
        return 0;
    }
    if (strcmp(argv[1], "CGI_encrypt") == 0) {
        const char *pw = "This is my C CGI test password";
        p = argv[2];
        p = CGI_encrypt(p, strlen(p), pw);
		printf("enc len = %d\n", strlen(p));
        p = CGI_decrypt(p , &i, pw);
		printf("dec len = %d %s\n", i, p);
        return 0;
    }
    return 0;
}