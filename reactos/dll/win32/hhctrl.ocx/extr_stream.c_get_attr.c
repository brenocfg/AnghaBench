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
 int /*<<< orphan*/  WARN (char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char*) ; 
 char tolower (char) ; 

const char *get_attr(const char *node, const char *name, int *len)
{
    const char *ptr, *ptr2;
    int name_len, node_len;
    char name_buf[32];
    char *node_buf;
    int i;

    /* Create a lower case copy of the node */
    node_len = strlen(node)+1;
    node_buf = heap_alloc(node_len*sizeof(char));
    if(!node_buf)
        return NULL;
    memcpy(node_buf, node, node_len);
    for(i=0;i<node_len;i++)
        node_buf[i] = tolower(node_buf[i]);
    /* Create a lower case copy of the attribute name (search string) */
    name_len = strlen(name);
    memcpy(name_buf, name, name_len);
    for(i=0;i<name_len;i++)
        name_buf[i] = tolower(name_buf[i]);
    name_buf[name_len++] = '=';
    name_buf[name_len++] = '\"';
    name_buf[name_len] = 0;

    ptr = strstr(node_buf, name_buf);
    if(!ptr) {
        WARN("name not found\n");
        heap_free(node_buf);
        return NULL;
    }

    ptr += name_len;
    ptr2 = strchr(ptr, '\"');
    if(!ptr2)
    {
        heap_free(node_buf);
        return NULL;
    }

    *len = ptr2-ptr;
    /* Return the pointer offset within the original string */
    ptr = node+(ptr-node_buf);

    heap_free(node_buf);
    return ptr;
}