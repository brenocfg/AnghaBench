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
 int SPIFFS_APPEND ; 
 int SPIFFS_CREAT ; 
 int SPIFFS_RDONLY ; 
 int SPIFFS_RDWR ; 
 int SPIFFS_TRUNC ; 
 int SPIFFS_WRONLY ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int fs_mode2flag(const char *mode){
  if(strlen(mode)==1){
  	if(strcmp(mode,"w")==0)
  	  return SPIFFS_WRONLY|SPIFFS_CREAT|SPIFFS_TRUNC;
  	else if(strcmp(mode, "r")==0)
  	  return SPIFFS_RDONLY;
  	else if(strcmp(mode, "a")==0)
  	  return SPIFFS_WRONLY|SPIFFS_CREAT|SPIFFS_APPEND;
  	else
  	  return SPIFFS_RDONLY;
  } else if (strlen(mode)==2){
  	if(strcmp(mode,"r+")==0)
  	  return SPIFFS_RDWR;
  	else if(strcmp(mode, "w+")==0)
  	  return SPIFFS_RDWR|SPIFFS_CREAT|SPIFFS_TRUNC;
  	else if(strcmp(mode, "a+")==0)
  	  return SPIFFS_RDWR|SPIFFS_CREAT|SPIFFS_APPEND;
  	else
  	  return SPIFFS_RDONLY;
  } else {
  	return SPIFFS_RDONLY;
  }
}