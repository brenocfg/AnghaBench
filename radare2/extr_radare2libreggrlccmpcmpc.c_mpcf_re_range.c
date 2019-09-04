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
typedef  char mpc_val_t ;
typedef  char mpc_parser_t ;

/* Variables and functions */
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mpc_fail (char*) ; 
 char* mpc_noneof (char*) ; 
 char* mpc_oneof (char*) ; 
 char* mpc_re_range_escape_char (char const) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static mpc_val_t *mpcf_re_range(mpc_val_t *x) {
  
  mpc_parser_t *out;
  size_t i, j;
  size_t start, end;
  const char *tmp = NULL;
  const char *s = x;
  int comp = s[0] == '^' ? 1 : 0;
  char *range;
  
  if (s[0] == '\0') { free(x); return mpc_fail("Invalid Regex Range Expression"); } 
  if (s[0] == '^' && 
      s[1] == '\0') { free(x); return mpc_fail("Invalid Regex Range Expression"); }
  
  range = calloc(1,1);

  for (i = comp; i < strlen(s); i++){
    
    /* Regex Range Escape */
    if (s[i] == '\\') {
      tmp = mpc_re_range_escape_char(s[i+1]);
      if (tmp != NULL) {
        range = realloc(range, strlen(range) + strlen(tmp) + 1);
        strcat(range, tmp);
      } else {
        range = realloc(range, strlen(range) + 1 + 1);
        range[strlen(range) + 1] = '\0';
        range[strlen(range) + 0] = s[i+1];      
      }
      i++;
    }
    
    /* Regex Range...Range */
    else if (s[i] == '-') {
      if (s[i+1] == '\0' || i == 0) {
          range = realloc(range, strlen(range) + strlen("-") + 1);
          strcat(range, "-");
      } else {
        start = s[i-1]+1;
        end = s[i+1]-1;
        for (j = start; j <= end; j++) {
          range = realloc(range, strlen(range) + 1 + 1 + 1);
          range[strlen(range) + 1] = '\0';
          range[strlen(range) + 0] = j;
        }        
      }
    }
    
    /* Regex Range Normal */
    else {
      range = realloc(range, strlen(range) + 1 + 1);
      range[strlen(range) + 1] = '\0';
      range[strlen(range) + 0] = s[i];
    }
  
  }
  
  out = comp == 1 ? mpc_noneof(range) : mpc_oneof(range);
  
  free(x);
  free(range);
  
  return out;
}