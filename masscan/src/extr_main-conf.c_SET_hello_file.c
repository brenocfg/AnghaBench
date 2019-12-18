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
struct Masscan {scalar_t__ echo; } ;
typedef  int /*<<< orphan*/  foo ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int ARRAY (char const*) ; 
 int CONF_ERR ; 
 int CONF_OK ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 size_t base64_encode (char*,int,char*,size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  masscan_set_parameter (struct Masscan*,char*,char*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int SET_hello_file(struct Masscan *masscan, const char *name, const char *value)
{
    unsigned index;
    FILE *fp;
    int x;
    char buf[16384];
    char buf2[16384];
    size_t bytes_read;
    size_t bytes_encoded;
    char foo[64];

    if (masscan->echo) {
        //Echoed as a string "hello-string" that was originally read
        //from a file, not the "hello-filename"
        return 0;
    }
    
    index = ARRAY(name);
    if (index >= 65536) {
        fprintf(stderr, "%s: bad index\n", name);
        return CONF_ERR;
    }

    /* When connecting via TCP, send this file */
    x = fopen_s(&fp, value, "rb");
    if (x != 0) {
        LOG(0, "[FAILED] could not read hello file\n");
        perror(value);
        return CONF_ERR;
    }
    
    bytes_read = fread(buf, 1, sizeof(buf), fp);
    if (bytes_read == 0) {
        LOG(0, "[FAILED] could not read hello file\n");
        perror(value);
        fclose(fp);
        return CONF_ERR;
    }
    fclose(fp);
    
    bytes_encoded = base64_encode(buf2, sizeof(buf2)-1, buf, bytes_read);
    buf2[bytes_encoded] = '\0';
    
    sprintf_s(foo, sizeof(foo), "hello-string[%u]", (unsigned)index);
    
    masscan_set_parameter(masscan, foo, buf2);

    return CONF_OK;
}